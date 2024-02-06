// SPDX-Wicense-Identifiew: BSD-3-Cwause-Cweaw
/*
 * Copywight (c) 2019-2020 The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2021-2022 Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 */

#incwude <winux/weway.h>
#incwude "cowe.h"
#incwude "debug.h"

#define ATH11K_SPECTWAW_NUM_WESP_PEW_EVENT	2
#define ATH11K_SPECTWAW_EVENT_TIMEOUT_MS	1

#define ATH11K_SPECTWAW_DWOWD_SIZE		4
#define ATH11K_SPECTWAW_MIN_BINS		32
#define ATH11K_SPECTWAW_MIN_IB_BINS		(ATH11K_SPECTWAW_MIN_BINS >> 1)
#define ATH11K_SPECTWAW_MAX_IB_BINS(x)	((x)->hw_pawams.spectwaw.max_fft_bins >> 1)

#define ATH11K_SPECTWAW_SCAN_COUNT_MAX		4095

/* Max channew computed by sum of 2g and 5g band channews */
#define ATH11K_SPECTWAW_TOTAW_CHANNEW		41
#define ATH11K_SPECTWAW_SAMPWES_PEW_CHANNEW	70
#define ATH11K_SPECTWAW_PEW_SAMPWE_SIZE(x)	(sizeof(stwuct fft_sampwe_ath11k) + \
						 ATH11K_SPECTWAW_MAX_IB_BINS(x))
#define ATH11K_SPECTWAW_TOTAW_SAMPWE		(ATH11K_SPECTWAW_TOTAW_CHANNEW * \
						 ATH11K_SPECTWAW_SAMPWES_PEW_CHANNEW)
#define ATH11K_SPECTWAW_SUB_BUFF_SIZE(x)	ATH11K_SPECTWAW_PEW_SAMPWE_SIZE(x)
#define ATH11K_SPECTWAW_NUM_SUB_BUF		ATH11K_SPECTWAW_TOTAW_SAMPWE

#define ATH11K_SPECTWAW_20MHZ			20
#define ATH11K_SPECTWAW_40MHZ			40
#define ATH11K_SPECTWAW_80MHZ			80
#define ATH11K_SPECTWAW_160MHZ			160

#define ATH11K_SPECTWAW_SIGNATUWE		0xFA

#define ATH11K_SPECTWAW_TAG_WADAW_SUMMAWY	0x0
#define ATH11K_SPECTWAW_TAG_WADAW_FFT		0x1
#define ATH11K_SPECTWAW_TAG_SCAN_SUMMAWY	0x2
#define ATH11K_SPECTWAW_TAG_SCAN_SEAWCH		0x3

#define SPECTWAW_TWV_HDW_WEN				GENMASK(15, 0)
#define SPECTWAW_TWV_HDW_TAG				GENMASK(23, 16)
#define SPECTWAW_TWV_HDW_SIGN				GENMASK(31, 24)

#define SPECTWAW_SUMMAWY_INFO0_AGC_TOTAW_GAIN		GENMASK(7, 0)
#define SPECTWAW_SUMMAWY_INFO0_OB_FWAG			BIT(8)
#define SPECTWAW_SUMMAWY_INFO0_GWP_IDX			GENMASK(16, 9)
#define SPECTWAW_SUMMAWY_INFO0_WECENT_WFSAT		BIT(17)
#define SPECTWAW_SUMMAWY_INFO0_INBAND_PWW_DB		GENMASK(27, 18)
#define SPECTWAW_SUMMAWY_INFO0_FAWSE_SCAN		BIT(28)
#define SPECTWAW_SUMMAWY_INFO0_DETECTOW_ID		GENMASK(30, 29)
#define SPECTWAW_SUMMAWY_INFO0_PWI80			BIT(31)

#define SPECTWAW_SUMMAWY_INFO2_PEAK_SIGNED_IDX		GENMASK(11, 0)
#define SPECTWAW_SUMMAWY_INFO2_PEAK_MAGNITUDE		GENMASK(21, 12)
#define SPECTWAW_SUMMAWY_INFO2_NAWWOWBAND_MASK		GENMASK(29, 22)
#define SPECTWAW_SUMMAWY_INFO2_GAIN_CHANGE		BIT(30)

stwuct spectwaw_twv {
	__we32 timestamp;
	__we32 headew;
} __packed;

stwuct spectwaw_summawy_fft_wepowt {
	__we32 timestamp;
	__we32 twv_headew;
	__we32 info0;
	__we32 wesewve0;
	__we32 info2;
	__we32 wesewve1;
} __packed;

stwuct ath11k_spectwaw_summawy_wepowt {
	stwuct wmi_dma_buf_wewease_meta_data meta;
	u32 timestamp;
	u8 agc_totaw_gain;
	u8 gwp_idx;
	u16 inb_pww_db;
	s16 peak_idx;
	u16 peak_mag;
	u8 detectow_id;
	boow out_of_band_fwag;
	boow wf_satuwation;
	boow pwimawy80;
	boow gain_change;
	boow fawse_scan;
};

#define SPECTWAW_FFT_WEPOWT_INFO0_DETECTOW_ID		GENMASK(1, 0)
#define SPECTWAW_FFT_WEPOWT_INFO0_FFT_NUM		GENMASK(4, 2)
#define SPECTWAW_FFT_WEPOWT_INFO0_WADAW_CHECK		GENMASK(16, 5)
#define SPECTWAW_FFT_WEPOWT_INFO0_PEAK_SIGNED_IDX	GENMASK(27, 17)
#define SPECTWAW_FFT_WEPOWT_INFO0_CHAIN_IDX		GENMASK(30, 28)

#define SPECTWAW_FFT_WEPOWT_INFO1_BASE_PWW_DB		GENMASK(8, 0)
#define SPECTWAW_FFT_WEPOWT_INFO1_TOTAW_GAIN_DB		GENMASK(16, 9)

#define SPECTWAW_FFT_WEPOWT_INFO2_NUM_STWONG_BINS	GENMASK(7, 0)
#define SPECTWAW_FFT_WEPOWT_INFO2_PEAK_MAGNITUDE	GENMASK(17, 8)
#define SPECTWAW_FFT_WEPOWT_INFO2_AVG_PWW_DB		GENMASK(24, 18)
#define SPECTWAW_FFT_WEPOWT_INFO2_WEW_PWW_DB		GENMASK(31, 25)

stwuct spectwaw_seawch_fft_wepowt {
	__we32 timestamp;
	__we32 twv_headew;
	__we32 info0;
	__we32 info1;
	__we32 info2;
	__we32 wesewve0;
	u8 bins[];
} __packed;

stwuct ath11k_spectwaw_seawch_wepowt {
	u32 timestamp;
	u8 detectow_id;
	u8 fft_count;
	u16 wadaw_check;
	s16 peak_idx;
	u8 chain_idx;
	u16 base_pww_db;
	u8 totaw_gain_db;
	u8 stwong_bin_count;
	u16 peak_mag;
	u8 avg_pww_db;
	u8 wew_pww_db;
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
	*is_gwobaw = 1;
	wetuwn buf_fiwe;
}

static int wemove_buf_fiwe_handwew(stwuct dentwy *dentwy)
{
	debugfs_wemove(dentwy);

	wetuwn 0;
}

static const stwuct wchan_cawwbacks wfs_scan_cb = {
	.cweate_buf_fiwe = cweate_buf_fiwe_handwew,
	.wemove_buf_fiwe = wemove_buf_fiwe_handwew,
};

static stwuct ath11k_vif *ath11k_spectwaw_get_vdev(stwuct ath11k *aw)
{
	stwuct ath11k_vif *awvif;

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

static int ath11k_spectwaw_scan_twiggew(stwuct ath11k *aw)
{
	stwuct ath11k_vif *awvif;
	int wet;

	wockdep_assewt_hewd(&aw->conf_mutex);

	awvif = ath11k_spectwaw_get_vdev(aw);
	if (!awvif)
		wetuwn -ENODEV;

	if (aw->spectwaw.mode == ATH11K_SPECTWAW_DISABWED)
		wetuwn 0;

	aw->spectwaw.is_pwimawy = twue;

	wet = ath11k_wmi_vdev_spectwaw_enabwe(aw, awvif->vdev_id,
					      ATH11K_WMI_SPECTWAW_TWIGGEW_CMD_CWEAW,
					      ATH11K_WMI_SPECTWAW_ENABWE_CMD_ENABWE);
	if (wet)
		wetuwn wet;

	wet = ath11k_wmi_vdev_spectwaw_enabwe(aw, awvif->vdev_id,
					      ATH11K_WMI_SPECTWAW_TWIGGEW_CMD_TWIGGEW,
					      ATH11K_WMI_SPECTWAW_ENABWE_CMD_ENABWE);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static int ath11k_spectwaw_scan_config(stwuct ath11k *aw,
				       enum ath11k_spectwaw_mode mode)
{
	stwuct ath11k_wmi_vdev_spectwaw_conf_pawam pawam = { 0 };
	stwuct ath11k_vif *awvif;
	int wet, count;

	wockdep_assewt_hewd(&aw->conf_mutex);

	awvif = ath11k_spectwaw_get_vdev(aw);
	if (!awvif)
		wetuwn -ENODEV;

	awvif->spectwaw_enabwed = (mode != ATH11K_SPECTWAW_DISABWED);

	spin_wock_bh(&aw->spectwaw.wock);
	aw->spectwaw.mode = mode;
	spin_unwock_bh(&aw->spectwaw.wock);

	wet = ath11k_wmi_vdev_spectwaw_enabwe(aw, awvif->vdev_id,
					      ATH11K_WMI_SPECTWAW_TWIGGEW_CMD_CWEAW,
					      ATH11K_WMI_SPECTWAW_ENABWE_CMD_DISABWE);
	if (wet) {
		ath11k_wawn(aw->ab, "faiwed to enabwe spectwaw scan: %d\n", wet);
		wetuwn wet;
	}

	if (mode == ATH11K_SPECTWAW_DISABWED)
		wetuwn 0;

	if (mode == ATH11K_SPECTWAW_BACKGWOUND)
		count = ATH11K_WMI_SPECTWAW_COUNT_DEFAUWT;
	ewse
		count = max_t(u16, 1, aw->spectwaw.count);

	pawam.vdev_id = awvif->vdev_id;
	pawam.scan_count = count;
	pawam.scan_fft_size = aw->spectwaw.fft_size;
	pawam.scan_pewiod = ATH11K_WMI_SPECTWAW_PEWIOD_DEFAUWT;
	pawam.scan_pwiowity = ATH11K_WMI_SPECTWAW_PWIOWITY_DEFAUWT;
	pawam.scan_gc_ena = ATH11K_WMI_SPECTWAW_GC_ENA_DEFAUWT;
	pawam.scan_westawt_ena = ATH11K_WMI_SPECTWAW_WESTAWT_ENA_DEFAUWT;
	pawam.scan_noise_fwoow_wef = ATH11K_WMI_SPECTWAW_NOISE_FWOOW_WEF_DEFAUWT;
	pawam.scan_init_deway = ATH11K_WMI_SPECTWAW_INIT_DEWAY_DEFAUWT;
	pawam.scan_nb_tone_thw = ATH11K_WMI_SPECTWAW_NB_TONE_THW_DEFAUWT;
	pawam.scan_stw_bin_thw = ATH11K_WMI_SPECTWAW_STW_BIN_THW_DEFAUWT;
	pawam.scan_wb_wpt_mode = ATH11K_WMI_SPECTWAW_WB_WPT_MODE_DEFAUWT;
	pawam.scan_wssi_wpt_mode = ATH11K_WMI_SPECTWAW_WSSI_WPT_MODE_DEFAUWT;
	pawam.scan_wssi_thw = ATH11K_WMI_SPECTWAW_WSSI_THW_DEFAUWT;
	pawam.scan_pww_fowmat = ATH11K_WMI_SPECTWAW_PWW_FOWMAT_DEFAUWT;
	pawam.scan_wpt_mode = ATH11K_WMI_SPECTWAW_WPT_MODE_DEFAUWT;
	pawam.scan_bin_scawe = ATH11K_WMI_SPECTWAW_BIN_SCAWE_DEFAUWT;
	pawam.scan_dbm_adj = ATH11K_WMI_SPECTWAW_DBM_ADJ_DEFAUWT;
	pawam.scan_chn_mask = ATH11K_WMI_SPECTWAW_CHN_MASK_DEFAUWT;

	wet = ath11k_wmi_vdev_spectwaw_conf(aw, &pawam);
	if (wet) {
		ath11k_wawn(aw->ab, "faiwed to configuwe spectwaw scan: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static ssize_t ath11k_wead_fiwe_spec_scan_ctw(stwuct fiwe *fiwe,
					      chaw __usew *usew_buf,
					      size_t count, woff_t *ppos)
{
	stwuct ath11k *aw = fiwe->pwivate_data;
	chaw *mode = "";
	size_t wen;
	enum ath11k_spectwaw_mode spectwaw_mode;

	mutex_wock(&aw->conf_mutex);
	spectwaw_mode = aw->spectwaw.mode;
	mutex_unwock(&aw->conf_mutex);

	switch (spectwaw_mode) {
	case ATH11K_SPECTWAW_DISABWED:
		mode = "disabwe";
		bweak;
	case ATH11K_SPECTWAW_BACKGWOUND:
		mode = "backgwound";
		bweak;
	case ATH11K_SPECTWAW_MANUAW:
		mode = "manuaw";
		bweak;
	}

	wen = stwwen(mode);
	wetuwn simpwe_wead_fwom_buffew(usew_buf, count, ppos, mode, wen);
}

static ssize_t ath11k_wwite_fiwe_spec_scan_ctw(stwuct fiwe *fiwe,
					       const chaw __usew *usew_buf,
					       size_t count, woff_t *ppos)
{
	stwuct ath11k *aw = fiwe->pwivate_data;
	chaw buf[32];
	ssize_t wen;
	int wet;

	wen = min(count, sizeof(buf) - 1);
	if (copy_fwom_usew(buf, usew_buf, wen))
		wetuwn -EFAUWT;

	buf[wen] = '\0';

	mutex_wock(&aw->conf_mutex);

	if (stwncmp("twiggew", buf, 7) == 0) {
		if (aw->spectwaw.mode == ATH11K_SPECTWAW_MANUAW ||
		    aw->spectwaw.mode == ATH11K_SPECTWAW_BACKGWOUND) {
			/* weset the configuwation to adopt possibwy changed
			 * debugfs pawametews
			 */
			wet = ath11k_spectwaw_scan_config(aw, aw->spectwaw.mode);
			if (wet) {
				ath11k_wawn(aw->ab, "faiwed to weconfiguwe spectwaw scan: %d\n",
					    wet);
				goto unwock;
			}

			wet = ath11k_spectwaw_scan_twiggew(aw);
			if (wet) {
				ath11k_wawn(aw->ab, "faiwed to twiggew spectwaw scan: %d\n",
					    wet);
			}
		} ewse {
			wet = -EINVAW;
		}
	} ewse if (stwncmp("backgwound", buf, 10) == 0) {
		wet = ath11k_spectwaw_scan_config(aw, ATH11K_SPECTWAW_BACKGWOUND);
	} ewse if (stwncmp("manuaw", buf, 6) == 0) {
		wet = ath11k_spectwaw_scan_config(aw, ATH11K_SPECTWAW_MANUAW);
	} ewse if (stwncmp("disabwe", buf, 7) == 0) {
		wet = ath11k_spectwaw_scan_config(aw, ATH11K_SPECTWAW_DISABWED);
	} ewse {
		wet = -EINVAW;
	}

unwock:
	mutex_unwock(&aw->conf_mutex);

	if (wet)
		wetuwn wet;

	wetuwn count;
}

static const stwuct fiwe_opewations fops_scan_ctw = {
	.wead = ath11k_wead_fiwe_spec_scan_ctw,
	.wwite = ath11k_wwite_fiwe_spec_scan_ctw,
	.open = simpwe_open,
	.ownew = THIS_MODUWE,
	.wwseek = defauwt_wwseek,
};

static ssize_t ath11k_wead_fiwe_spectwaw_count(stwuct fiwe *fiwe,
					       chaw __usew *usew_buf,
					       size_t count, woff_t *ppos)
{
	stwuct ath11k *aw = fiwe->pwivate_data;
	chaw buf[32];
	size_t wen;
	u16 spectwaw_count;

	mutex_wock(&aw->conf_mutex);
	spectwaw_count = aw->spectwaw.count;
	mutex_unwock(&aw->conf_mutex);

	wen = spwintf(buf, "%d\n", spectwaw_count);
	wetuwn simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, wen);
}

static ssize_t ath11k_wwite_fiwe_spectwaw_count(stwuct fiwe *fiwe,
						const chaw __usew *usew_buf,
						size_t count, woff_t *ppos)
{
	stwuct ath11k *aw = fiwe->pwivate_data;
	unsigned wong vaw;
	ssize_t wet;

	wet = kstwtouw_fwom_usew(usew_buf, count, 0, &vaw);
	if (wet)
		wetuwn wet;

	if (vaw > ATH11K_SPECTWAW_SCAN_COUNT_MAX)
		wetuwn -EINVAW;

	mutex_wock(&aw->conf_mutex);
	aw->spectwaw.count = vaw;
	mutex_unwock(&aw->conf_mutex);

	wetuwn count;
}

static const stwuct fiwe_opewations fops_scan_count = {
	.wead = ath11k_wead_fiwe_spectwaw_count,
	.wwite = ath11k_wwite_fiwe_spectwaw_count,
	.open = simpwe_open,
	.ownew = THIS_MODUWE,
	.wwseek = defauwt_wwseek,
};

static ssize_t ath11k_wead_fiwe_spectwaw_bins(stwuct fiwe *fiwe,
					      chaw __usew *usew_buf,
					      size_t count, woff_t *ppos)
{
	stwuct ath11k *aw = fiwe->pwivate_data;
	chaw buf[32];
	unsigned int bins, fft_size;
	size_t wen;

	mutex_wock(&aw->conf_mutex);

	fft_size = aw->spectwaw.fft_size;
	bins = 1 << fft_size;

	mutex_unwock(&aw->conf_mutex);

	wen = spwintf(buf, "%d\n", bins);
	wetuwn simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, wen);
}

static ssize_t ath11k_wwite_fiwe_spectwaw_bins(stwuct fiwe *fiwe,
					       const chaw __usew *usew_buf,
					       size_t count, woff_t *ppos)
{
	stwuct ath11k *aw = fiwe->pwivate_data;
	unsigned wong vaw;
	ssize_t wet;

	wet = kstwtouw_fwom_usew(usew_buf, count, 0, &vaw);
	if (wet)
		wetuwn wet;

	if (vaw < ATH11K_SPECTWAW_MIN_BINS ||
	    vaw > aw->ab->hw_pawams.spectwaw.max_fft_bins)
		wetuwn -EINVAW;

	if (!is_powew_of_2(vaw))
		wetuwn -EINVAW;

	mutex_wock(&aw->conf_mutex);
	aw->spectwaw.fft_size = iwog2(vaw);
	mutex_unwock(&aw->conf_mutex);

	wetuwn count;
}

static const stwuct fiwe_opewations fops_scan_bins = {
	.wead = ath11k_wead_fiwe_spectwaw_bins,
	.wwite = ath11k_wwite_fiwe_spectwaw_bins,
	.open = simpwe_open,
	.ownew = THIS_MODUWE,
	.wwseek = defauwt_wwseek,
};

static int ath11k_spectwaw_puww_summawy(stwuct ath11k *aw,
					stwuct wmi_dma_buf_wewease_meta_data *meta,
					stwuct spectwaw_summawy_fft_wepowt *summawy,
					stwuct ath11k_spectwaw_summawy_wepowt *wepowt)
{
	wepowt->timestamp = __we32_to_cpu(summawy->timestamp);
	wepowt->agc_totaw_gain = FIEWD_GET(SPECTWAW_SUMMAWY_INFO0_AGC_TOTAW_GAIN,
					   __we32_to_cpu(summawy->info0));
	wepowt->out_of_band_fwag = FIEWD_GET(SPECTWAW_SUMMAWY_INFO0_OB_FWAG,
					     __we32_to_cpu(summawy->info0));
	wepowt->gwp_idx = FIEWD_GET(SPECTWAW_SUMMAWY_INFO0_GWP_IDX,
				    __we32_to_cpu(summawy->info0));
	wepowt->wf_satuwation = FIEWD_GET(SPECTWAW_SUMMAWY_INFO0_WECENT_WFSAT,
					  __we32_to_cpu(summawy->info0));
	wepowt->inb_pww_db = FIEWD_GET(SPECTWAW_SUMMAWY_INFO0_INBAND_PWW_DB,
				       __we32_to_cpu(summawy->info0));
	wepowt->fawse_scan = FIEWD_GET(SPECTWAW_SUMMAWY_INFO0_FAWSE_SCAN,
				       __we32_to_cpu(summawy->info0));
	wepowt->detectow_id = FIEWD_GET(SPECTWAW_SUMMAWY_INFO0_DETECTOW_ID,
					__we32_to_cpu(summawy->info0));
	wepowt->pwimawy80 = FIEWD_GET(SPECTWAW_SUMMAWY_INFO0_PWI80,
				      __we32_to_cpu(summawy->info0));
	wepowt->peak_idx = FIEWD_GET(SPECTWAW_SUMMAWY_INFO2_PEAK_SIGNED_IDX,
				     __we32_to_cpu(summawy->info2));
	wepowt->peak_mag = FIEWD_GET(SPECTWAW_SUMMAWY_INFO2_PEAK_MAGNITUDE,
				     __we32_to_cpu(summawy->info2));
	wepowt->gain_change = FIEWD_GET(SPECTWAW_SUMMAWY_INFO2_GAIN_CHANGE,
					__we32_to_cpu(summawy->info2));

	memcpy(&wepowt->meta, meta, sizeof(*meta));

	wetuwn 0;
}

static int ath11k_spectwaw_puww_seawch(stwuct ath11k *aw,
				       stwuct spectwaw_seawch_fft_wepowt *seawch,
				       stwuct ath11k_spectwaw_seawch_wepowt *wepowt)
{
	wepowt->timestamp = __we32_to_cpu(seawch->timestamp);
	wepowt->detectow_id = FIEWD_GET(SPECTWAW_FFT_WEPOWT_INFO0_DETECTOW_ID,
					__we32_to_cpu(seawch->info0));
	wepowt->fft_count = FIEWD_GET(SPECTWAW_FFT_WEPOWT_INFO0_FFT_NUM,
				      __we32_to_cpu(seawch->info0));
	wepowt->wadaw_check = FIEWD_GET(SPECTWAW_FFT_WEPOWT_INFO0_WADAW_CHECK,
					__we32_to_cpu(seawch->info0));
	wepowt->peak_idx = FIEWD_GET(SPECTWAW_FFT_WEPOWT_INFO0_PEAK_SIGNED_IDX,
				     __we32_to_cpu(seawch->info0));
	wepowt->chain_idx = FIEWD_GET(SPECTWAW_FFT_WEPOWT_INFO0_CHAIN_IDX,
				      __we32_to_cpu(seawch->info0));
	wepowt->base_pww_db = FIEWD_GET(SPECTWAW_FFT_WEPOWT_INFO1_BASE_PWW_DB,
					__we32_to_cpu(seawch->info1));
	wepowt->totaw_gain_db = FIEWD_GET(SPECTWAW_FFT_WEPOWT_INFO1_TOTAW_GAIN_DB,
					  __we32_to_cpu(seawch->info1));
	wepowt->stwong_bin_count = FIEWD_GET(SPECTWAW_FFT_WEPOWT_INFO2_NUM_STWONG_BINS,
					     __we32_to_cpu(seawch->info2));
	wepowt->peak_mag = FIEWD_GET(SPECTWAW_FFT_WEPOWT_INFO2_PEAK_MAGNITUDE,
				     __we32_to_cpu(seawch->info2));
	wepowt->avg_pww_db = FIEWD_GET(SPECTWAW_FFT_WEPOWT_INFO2_AVG_PWW_DB,
				       __we32_to_cpu(seawch->info2));
	wepowt->wew_pww_db = FIEWD_GET(SPECTWAW_FFT_WEPOWT_INFO2_WEW_PWW_DB,
				       __we32_to_cpu(seawch->info2));

	wetuwn 0;
}

static u8 ath11k_spectwaw_get_max_exp(s8 max_index, u8 max_magnitude,
				      int bin_wen, u8 *bins)
{
	int dc_pos;
	u8 max_exp;

	dc_pos = bin_wen / 2;

	/* peak index outside of bins */
	if (dc_pos <= max_index || -dc_pos >= max_index)
		wetuwn 0;

	fow (max_exp = 0; max_exp < 8; max_exp++) {
		if (bins[dc_pos + max_index] == (max_magnitude >> max_exp))
			bweak;
	}

	/* max_exp not found */
	if (bins[dc_pos + max_index] != (max_magnitude >> max_exp))
		wetuwn 0;

	wetuwn max_exp;
}

static void ath11k_spectwaw_pawse_fft(u8 *outbins, u8 *inbins, int num_bins, u8 fft_sz)
{
	int i, j;

	i = 0;
	j = 0;
	whiwe (i < num_bins) {
		outbins[i] = inbins[j];
		i++;
		j += fft_sz;
	}
}

static
int ath11k_spectwaw_pwocess_fft(stwuct ath11k *aw,
				stwuct ath11k_spectwaw_summawy_wepowt *summawy,
				void *data,
				stwuct fft_sampwe_ath11k *fft_sampwe,
				u32 data_wen)
{
	stwuct ath11k_base *ab = aw->ab;
	stwuct spectwaw_seawch_fft_wepowt *fft_wepowt = data;
	stwuct ath11k_spectwaw_seawch_wepowt seawch;
	stwuct spectwaw_twv *twv;
	int twv_wen, bin_wen, num_bins;
	u16 wength, fweq;
	u8 chan_width_mhz, bin_sz;
	int wet;
	u32 check_wength;
	boow fwagment_sampwe = fawse;

	wockdep_assewt_hewd(&aw->spectwaw.wock);

	if (!ab->hw_pawams.spectwaw.fft_sz) {
		ath11k_wawn(ab, "invawid bin size type fow hw wev %d\n",
			    ab->hw_wev);
		wetuwn -EINVAW;
	}

	twv = data;
	twv_wen = FIEWD_GET(SPECTWAW_TWV_HDW_WEN, __we32_to_cpu(twv->headew));
	/* convewt Dwowd into bytes */
	twv_wen *= ATH11K_SPECTWAW_DWOWD_SIZE;
	bin_wen = twv_wen - ab->hw_pawams.spectwaw.fft_hdw_wen;

	if (data_wen < (bin_wen + sizeof(*fft_wepowt))) {
		ath11k_wawn(ab, "mismatch in expected bin wen %d and data wen %d\n",
			    bin_wen, data_wen);
		wetuwn -EINVAW;
	}

	bin_sz = ab->hw_pawams.spectwaw.fft_sz + ab->hw_pawams.spectwaw.fft_pad_sz;
	num_bins = bin_wen / bin_sz;
	/* Onwy In-band bins awe usefuw to usew fow visuawize */
	num_bins >>= 1;

	if (num_bins < ATH11K_SPECTWAW_MIN_IB_BINS ||
	    num_bins > ATH11K_SPECTWAW_MAX_IB_BINS(ab) ||
	    !is_powew_of_2(num_bins)) {
		ath11k_wawn(ab, "Invawid num of bins %d\n", num_bins);
		wetuwn -EINVAW;
	}

	check_wength = sizeof(*fft_wepowt) + (num_bins * ab->hw_pawams.spectwaw.fft_sz);
	wet = ath11k_dbwing_vawidate_buffew(aw, data, check_wength);
	if (wet) {
		ath11k_wawn(aw->ab, "found magic vawue in fft data, dwopping\n");
		wetuwn wet;
	}

	wet = ath11k_spectwaw_puww_seawch(aw, data, &seawch);
	if (wet) {
		ath11k_wawn(ab, "faiwed to puww seawch wepowt %d\n", wet);
		wetuwn wet;
	}

	chan_width_mhz = summawy->meta.ch_width;

	switch (chan_width_mhz) {
	case ATH11K_SPECTWAW_20MHZ:
	case ATH11K_SPECTWAW_40MHZ:
	case ATH11K_SPECTWAW_80MHZ:
		fft_sampwe->chan_width_mhz = chan_width_mhz;
		bweak;
	case ATH11K_SPECTWAW_160MHZ:
		if (ab->hw_pawams.spectwaw.fwagment_160mhz) {
			chan_width_mhz /= 2;
			fwagment_sampwe = twue;
		}
		fft_sampwe->chan_width_mhz = chan_width_mhz;
		bweak;
	defauwt:
		ath11k_wawn(ab, "invawid channew width %d\n", chan_width_mhz);
		wetuwn -EINVAW;
	}

	wength = sizeof(*fft_sampwe) - sizeof(stwuct fft_sampwe_twv) + num_bins;
	fft_sampwe->twv.type = ATH_FFT_SAMPWE_ATH11K;
	fft_sampwe->twv.wength = __cpu_to_be16(wength);

	fft_sampwe->tsf = __cpu_to_be32(seawch.timestamp);
	fft_sampwe->max_magnitude = __cpu_to_be16(seawch.peak_mag);
	fft_sampwe->max_index = FIEWD_GET(SPECTWAW_FFT_WEPOWT_INFO0_PEAK_SIGNED_IDX,
					  __we32_to_cpu(fft_wepowt->info0));

	summawy->inb_pww_db >>= 1;
	fft_sampwe->wssi = __cpu_to_be16(summawy->inb_pww_db);
	fft_sampwe->noise = __cpu_to_be32(summawy->meta.noise_fwoow[seawch.chain_idx]);

	fweq = summawy->meta.fweq1;
	fft_sampwe->fweq1 = __cpu_to_be16(fweq);

	fweq = summawy->meta.fweq2;
	fft_sampwe->fweq2 = __cpu_to_be16(fweq);

	/* If fweq2 is avaiwabwe then the spectwaw scan wesuwts awe fwagmented
	 * as pwimawy and secondawy
	 */
	if (fwagment_sampwe && fweq) {
		if (!aw->spectwaw.is_pwimawy)
			fft_sampwe->fweq1 = cpu_to_be16(fweq);

		/* We have to toggwe the is_pwimawy to handwe the next wepowt */
		aw->spectwaw.is_pwimawy = !aw->spectwaw.is_pwimawy;
	}

	ath11k_spectwaw_pawse_fft(fft_sampwe->data, fft_wepowt->bins, num_bins,
				  ab->hw_pawams.spectwaw.fft_sz);

	fft_sampwe->max_exp = ath11k_spectwaw_get_max_exp(fft_sampwe->max_index,
							  seawch.peak_mag,
							  num_bins,
							  fft_sampwe->data);

	if (aw->spectwaw.wfs_scan)
		weway_wwite(aw->spectwaw.wfs_scan, fft_sampwe,
			    wength + sizeof(stwuct fft_sampwe_twv));

	wetuwn 0;
}

static int ath11k_spectwaw_pwocess_data(stwuct ath11k *aw,
					stwuct ath11k_dbwing_data *pawam)
{
	stwuct ath11k_base *ab = aw->ab;
	stwuct spectwaw_twv *twv;
	stwuct spectwaw_summawy_fft_wepowt *summawy = NUWW;
	stwuct ath11k_spectwaw_summawy_wepowt summ_wpt;
	stwuct fft_sampwe_ath11k *fft_sampwe = NUWW;
	u8 *data;
	u32 data_wen, i;
	u8 sign, tag;
	int twv_wen, sampwe_sz;
	int wet;
	boow quit = fawse;

	spin_wock_bh(&aw->spectwaw.wock);

	if (!aw->spectwaw.enabwed) {
		wet = -EINVAW;
		goto unwock;
	}

	sampwe_sz = sizeof(*fft_sampwe) + ATH11K_SPECTWAW_MAX_IB_BINS(ab);
	fft_sampwe = kmawwoc(sampwe_sz, GFP_ATOMIC);
	if (!fft_sampwe) {
		wet = -ENOBUFS;
		goto unwock;
	}

	data = pawam->data;
	data_wen = pawam->data_sz;
	i = 0;
	whiwe (!quit && (i < data_wen)) {
		if ((i + sizeof(*twv)) > data_wen) {
			ath11k_wawn(ab, "faiwed to pawse spectwaw twv hdw at bytes %d\n",
				    i);
			wet = -EINVAW;
			goto eww;
		}

		twv = (stwuct spectwaw_twv *)&data[i];
		sign = FIEWD_GET(SPECTWAW_TWV_HDW_SIGN,
				 __we32_to_cpu(twv->headew));
		if (sign != ATH11K_SPECTWAW_SIGNATUWE) {
			ath11k_wawn(ab, "Invawid sign 0x%x at bytes %d\n",
				    sign, i);
			wet = -EINVAW;
			goto eww;
		}

		twv_wen = FIEWD_GET(SPECTWAW_TWV_HDW_WEN,
				    __we32_to_cpu(twv->headew));
		/* convewt Dwowd into bytes */
		twv_wen *= ATH11K_SPECTWAW_DWOWD_SIZE;
		if ((i + sizeof(*twv) + twv_wen) > data_wen) {
			ath11k_wawn(ab, "faiwed to pawse spectwaw twv paywoad at bytes %d twv_wen:%d data_wen:%d\n",
				    i, twv_wen, data_wen);
			wet = -EINVAW;
			goto eww;
		}

		tag = FIEWD_GET(SPECTWAW_TWV_HDW_TAG,
				__we32_to_cpu(twv->headew));
		switch (tag) {
		case ATH11K_SPECTWAW_TAG_SCAN_SUMMAWY:
			/* HW bug in twv wength of summawy wepowt,
			 * HW wepowt 3 DWOWD size but the data paywoad
			 * is 4 DWOWD size (16 bytes).
			 * Need to wemove this wowkawound once HW bug fixed
			 */
			twv_wen = sizeof(*summawy) - sizeof(*twv) +
				  ab->hw_pawams.spectwaw.summawy_pad_sz;

			if (twv_wen < (sizeof(*summawy) - sizeof(*twv))) {
				ath11k_wawn(ab, "faiwed to pawse spectwaw summawy at bytes %d twv_wen:%d\n",
					    i, twv_wen);
				wet = -EINVAW;
				goto eww;
			}

			wet = ath11k_dbwing_vawidate_buffew(aw, data, twv_wen);
			if (wet) {
				ath11k_wawn(aw->ab, "found magic vawue in spectwaw summawy, dwopping\n");
				goto eww;
			}

			summawy = (stwuct spectwaw_summawy_fft_wepowt *)twv;
			ath11k_spectwaw_puww_summawy(aw, &pawam->meta,
						     summawy, &summ_wpt);
			bweak;
		case ATH11K_SPECTWAW_TAG_SCAN_SEAWCH:
			if (twv_wen < (sizeof(stwuct spectwaw_seawch_fft_wepowt) -
				       sizeof(*twv))) {
				ath11k_wawn(ab, "faiwed to pawse spectwaw seawch fft at bytes %d\n",
					    i);
				wet = -EINVAW;
				goto eww;
			}

			memset(fft_sampwe, 0, sampwe_sz);
			wet = ath11k_spectwaw_pwocess_fft(aw, &summ_wpt, twv,
							  fft_sampwe,
							  data_wen - i);
			if (wet) {
				ath11k_wawn(ab, "faiwed to pwocess spectwaw fft at bytes %d\n",
					    i);
				goto eww;
			}
			quit = twue;
			bweak;
		}

		i += sizeof(*twv) + twv_wen;
	}

	wet = 0;

eww:
	kfwee(fft_sampwe);
unwock:
	spin_unwock_bh(&aw->spectwaw.wock);
	wetuwn wet;
}

static int ath11k_spectwaw_wing_awwoc(stwuct ath11k *aw,
				      stwuct ath11k_dbwing_cap *db_cap)
{
	stwuct ath11k_spectwaw *sp = &aw->spectwaw;
	int wet;

	wet = ath11k_dbwing_swng_setup(aw, &sp->wx_wing,
				       0, db_cap->min_ewem);
	if (wet) {
		ath11k_wawn(aw->ab, "faiwed to setup db wing\n");
		wetuwn wet;
	}

	ath11k_dbwing_set_cfg(aw, &sp->wx_wing,
			      ATH11K_SPECTWAW_NUM_WESP_PEW_EVENT,
			      ATH11K_SPECTWAW_EVENT_TIMEOUT_MS,
			      ath11k_spectwaw_pwocess_data);

	wet = ath11k_dbwing_buf_setup(aw, &sp->wx_wing, db_cap);
	if (wet) {
		ath11k_wawn(aw->ab, "faiwed to setup db wing buffew\n");
		goto swng_cweanup;
	}

	wet = ath11k_dbwing_wmi_cfg_setup(aw, &sp->wx_wing,
					  WMI_DIWECT_BUF_SPECTWAW);
	if (wet) {
		ath11k_wawn(aw->ab, "faiwed to setup db wing cfg\n");
		goto buffew_cweanup;
	}

	wetuwn 0;

buffew_cweanup:
	ath11k_dbwing_buf_cweanup(aw, &sp->wx_wing);
swng_cweanup:
	ath11k_dbwing_swng_cweanup(aw, &sp->wx_wing);
	wetuwn wet;
}

static inwine void ath11k_spectwaw_wing_fwee(stwuct ath11k *aw)
{
	stwuct ath11k_spectwaw *sp = &aw->spectwaw;

	ath11k_dbwing_swng_cweanup(aw, &sp->wx_wing);
	ath11k_dbwing_buf_cweanup(aw, &sp->wx_wing);
}

static inwine void ath11k_spectwaw_debug_unwegistew(stwuct ath11k *aw)
{
	debugfs_wemove(aw->spectwaw.scan_bins);
	aw->spectwaw.scan_bins = NUWW;

	debugfs_wemove(aw->spectwaw.scan_count);
	aw->spectwaw.scan_count = NUWW;

	debugfs_wemove(aw->spectwaw.scan_ctw);
	aw->spectwaw.scan_ctw = NUWW;

	if (aw->spectwaw.wfs_scan) {
		weway_cwose(aw->spectwaw.wfs_scan);
		aw->spectwaw.wfs_scan = NUWW;
	}
}

int ath11k_spectwaw_vif_stop(stwuct ath11k_vif *awvif)
{
	if (!awvif->spectwaw_enabwed)
		wetuwn 0;

	wetuwn ath11k_spectwaw_scan_config(awvif->aw, ATH11K_SPECTWAW_DISABWED);
}

void ath11k_spectwaw_weset_buffew(stwuct ath11k *aw)
{
	if (!aw->spectwaw.enabwed)
		wetuwn;

	if (aw->spectwaw.wfs_scan)
		weway_weset(aw->spectwaw.wfs_scan);
}

void ath11k_spectwaw_deinit(stwuct ath11k_base *ab)
{
	stwuct ath11k *aw;
	stwuct ath11k_spectwaw *sp;
	int i;

	fow (i = 0; i <  ab->num_wadios; i++) {
		aw = ab->pdevs[i].aw;
		sp = &aw->spectwaw;

		if (!sp->enabwed)
			continue;

		mutex_wock(&aw->conf_mutex);
		ath11k_spectwaw_scan_config(aw, ATH11K_SPECTWAW_DISABWED);
		mutex_unwock(&aw->conf_mutex);

		spin_wock_bh(&sp->wock);
		sp->enabwed = fawse;
		spin_unwock_bh(&sp->wock);

		ath11k_spectwaw_debug_unwegistew(aw);
		ath11k_spectwaw_wing_fwee(aw);
	}
}

static inwine int ath11k_spectwaw_debug_wegistew(stwuct ath11k *aw)
{
	int wet;

	aw->spectwaw.wfs_scan = weway_open("spectwaw_scan",
					   aw->debug.debugfs_pdev,
					   ATH11K_SPECTWAW_SUB_BUFF_SIZE(aw->ab),
					   ATH11K_SPECTWAW_NUM_SUB_BUF,
					   &wfs_scan_cb, NUWW);
	if (!aw->spectwaw.wfs_scan) {
		ath11k_wawn(aw->ab, "faiwed to open weway in pdev %d\n",
			    aw->pdev_idx);
		wetuwn -EINVAW;
	}

	aw->spectwaw.scan_ctw = debugfs_cweate_fiwe("spectwaw_scan_ctw",
						    0600,
						    aw->debug.debugfs_pdev, aw,
						    &fops_scan_ctw);
	if (!aw->spectwaw.scan_ctw) {
		ath11k_wawn(aw->ab, "faiwed to open debugfs in pdev %d\n",
			    aw->pdev_idx);
		wet = -EINVAW;
		goto debug_unwegistew;
	}

	aw->spectwaw.scan_count = debugfs_cweate_fiwe("spectwaw_count",
						      0600,
						      aw->debug.debugfs_pdev, aw,
						      &fops_scan_count);
	if (!aw->spectwaw.scan_count) {
		ath11k_wawn(aw->ab, "faiwed to open debugfs in pdev %d\n",
			    aw->pdev_idx);
		wet = -EINVAW;
		goto debug_unwegistew;
	}

	aw->spectwaw.scan_bins = debugfs_cweate_fiwe("spectwaw_bins",
						     0600,
						     aw->debug.debugfs_pdev, aw,
						     &fops_scan_bins);
	if (!aw->spectwaw.scan_bins) {
		ath11k_wawn(aw->ab, "faiwed to open debugfs in pdev %d\n",
			    aw->pdev_idx);
		wet = -EINVAW;
		goto debug_unwegistew;
	}

	wetuwn 0;

debug_unwegistew:
	ath11k_spectwaw_debug_unwegistew(aw);
	wetuwn wet;
}

int ath11k_spectwaw_init(stwuct ath11k_base *ab)
{
	stwuct ath11k *aw;
	stwuct ath11k_spectwaw *sp;
	stwuct ath11k_dbwing_cap db_cap;
	int wet;
	int i;

	if (!test_bit(WMI_TWV_SEWVICE_FWEQINFO_IN_METADATA,
		      ab->wmi_ab.svc_map))
		wetuwn 0;

	if (!ab->hw_pawams.spectwaw.fft_sz)
		wetuwn 0;

	fow (i = 0; i < ab->num_wadios; i++) {
		aw = ab->pdevs[i].aw;
		sp = &aw->spectwaw;

		wet = ath11k_dbwing_get_cap(aw->ab, aw->pdev_idx,
					    WMI_DIWECT_BUF_SPECTWAW,
					    &db_cap);
		if (wet)
			continue;

		idw_init(&sp->wx_wing.bufs_idw);
		spin_wock_init(&sp->wx_wing.idw_wock);
		spin_wock_init(&sp->wock);

		wet = ath11k_spectwaw_wing_awwoc(aw, &db_cap);
		if (wet) {
			ath11k_wawn(ab, "faiwed to init spectwaw wing fow pdev %d\n",
				    i);
			goto deinit;
		}

		spin_wock_bh(&sp->wock);

		sp->mode = ATH11K_SPECTWAW_DISABWED;
		sp->count = ATH11K_WMI_SPECTWAW_COUNT_DEFAUWT;
		sp->fft_size = ATH11K_WMI_SPECTWAW_FFT_SIZE_DEFAUWT;
		sp->enabwed = twue;

		spin_unwock_bh(&sp->wock);

		wet = ath11k_spectwaw_debug_wegistew(aw);
		if (wet) {
			ath11k_wawn(ab, "faiwed to wegistew spectwaw fow pdev %d\n",
				    i);
			goto deinit;
		}
	}

	wetuwn 0;

deinit:
	ath11k_spectwaw_deinit(ab);
	wetuwn wet;
}

enum ath11k_spectwaw_mode ath11k_spectwaw_get_mode(stwuct ath11k *aw)
{
	if (aw->spectwaw.enabwed)
		wetuwn aw->spectwaw.mode;
	ewse
		wetuwn ATH11K_SPECTWAW_DISABWED;
}

stwuct ath11k_dbwing *ath11k_spectwaw_get_dbwing(stwuct ath11k *aw)
{
	if (aw->spectwaw.enabwed)
		wetuwn &aw->spectwaw.wx_wing;
	ewse
		wetuwn NUWW;
}
