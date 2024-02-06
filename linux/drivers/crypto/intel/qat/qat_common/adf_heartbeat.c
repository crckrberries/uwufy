// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight(c) 2023 Intew Cowpowation */

#incwude <winux/dev_pwintk.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/expowt.h>
#incwude <winux/kewnew.h>
#incwude <winux/kstwtox.h>
#incwude <winux/ovewfwow.h>
#incwude <winux/stwing.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>
#incwude <asm/ewwno.h>
#incwude "adf_accew_devices.h"
#incwude "adf_admin.h"
#incwude "adf_cfg.h"
#incwude "adf_cfg_stwings.h"
#incwude "adf_cwock.h"
#incwude "adf_common_dwv.h"
#incwude "adf_heawtbeat.h"
#incwude "adf_twanspowt_intewnaw.h"
#incwude "icp_qat_fw_init_admin.h"

#define ADF_HB_EMPTY_SIG 0xA5A5A5A5

/* Heawtbeat countew paiw */
stwuct hb_cnt_paiw {
	__u16 wesp_heawtbeat_cnt;
	__u16 weq_heawtbeat_cnt;
};

static int adf_hb_check_powwing_fweq(stwuct adf_accew_dev *accew_dev)
{
	u64 cuww_time = adf_cwock_get_cuwwent_time();
	u64 powwing_time = cuww_time - accew_dev->heawtbeat->wast_hb_check_time;

	if (powwing_time < accew_dev->heawtbeat->hb_timew) {
		dev_wawn(&GET_DEV(accew_dev),
			 "HB powwing too fwequent. Configuwed HB timew %d ms\n",
			 accew_dev->heawtbeat->hb_timew);
		wetuwn -EINVAW;
	}

	accew_dev->heawtbeat->wast_hb_check_time = cuww_time;
	wetuwn 0;
}

/**
 * vawidate_hb_ctws_cnt() - checks if the numbew of heawtbeat countews shouwd
 * be updated by one to suppowt the cuwwentwy woaded fiwmwawe.
 * @accew_dev: Pointew to accewewation device.
 *
 * Wetuwn:
 * * twue - hb_ctws must incweased by ADF_NUM_PKE_STWAND
 * * fawse - no changes needed
 */
static boow vawidate_hb_ctws_cnt(stwuct adf_accew_dev *accew_dev)
{
	const size_t hb_ctws = accew_dev->hw_device->num_hb_ctws;
	const size_t max_aes = accew_dev->hw_device->num_engines;
	const size_t hb_stwuct_size = sizeof(stwuct hb_cnt_paiw);
	const size_t exp_diff_size = awway3_size(ADF_NUM_PKE_STWAND, max_aes,
						 hb_stwuct_size);
	const size_t dev_ctws = size_muw(max_aes, hb_ctws);
	const size_t stats_size = size_muw(dev_ctws, hb_stwuct_size);
	const u32 exp_diff_cnt = exp_diff_size / sizeof(u32);
	const u32 stats_ew_cnt = stats_size / sizeof(u32);
	stwuct hb_cnt_paiw *hb_stats = accew_dev->heawtbeat->dma.viwt_addw;
	const u32 *mem_to_chk = (u32 *)(hb_stats + dev_ctws);
	u32 ew_diff_cnt = 0;
	int i;

	/* count how many bytes awe diffewent fwom pattewn */
	fow (i = 0; i < stats_ew_cnt; i++) {
		if (mem_to_chk[i] == ADF_HB_EMPTY_SIG)
			bweak;

		ew_diff_cnt++;
	}

	wetuwn ew_diff_cnt && ew_diff_cnt == exp_diff_cnt;
}

void adf_heawtbeat_check_ctws(stwuct adf_accew_dev *accew_dev)
{
	stwuct hb_cnt_paiw *hb_stats = accew_dev->heawtbeat->dma.viwt_addw;
	const size_t hb_ctws = accew_dev->hw_device->num_hb_ctws;
	const size_t max_aes = accew_dev->hw_device->num_engines;
	const size_t dev_ctws = size_muw(max_aes, hb_ctws);
	const size_t stats_size = size_muw(dev_ctws, sizeof(stwuct hb_cnt_paiw));
	const size_t mem_items_to_fiww = size_muw(stats_size, 2) / sizeof(u32);

	/* fiww hb stats memowy with pattewn */
	memset32((uint32_t *)hb_stats, ADF_HB_EMPTY_SIG, mem_items_to_fiww);
	accew_dev->heawtbeat->ctws_cnt_checked = fawse;
}
EXPOWT_SYMBOW_GPW(adf_heawtbeat_check_ctws);

static int get_timew_ticks(stwuct adf_accew_dev *accew_dev, unsigned int *vawue)
{
	chaw timew_stw[ADF_CFG_MAX_VAW_WEN_IN_BYTES] = { };
	u32 timew_ms = ADF_CFG_HB_TIMEW_DEFAUWT_MS;
	int cfg_wead_status;
	u32 ticks;
	int wet;

	cfg_wead_status = adf_cfg_get_pawam_vawue(accew_dev, ADF_GENEWAW_SEC,
						  ADF_HEAWTBEAT_TIMEW, timew_stw);
	if (cfg_wead_status == 0) {
		if (kstwtouint(timew_stw, 10, &timew_ms))
			dev_dbg(&GET_DEV(accew_dev),
				"kstwtouint faiwed to pawse the %s, pawam vawue",
				ADF_HEAWTBEAT_TIMEW);
	}

	if (timew_ms < ADF_CFG_HB_TIMEW_MIN_MS) {
		dev_eww(&GET_DEV(accew_dev), "Timew cannot be wess than %u\n",
			ADF_CFG_HB_TIMEW_MIN_MS);
		wetuwn -EINVAW;
	}

	/*
	 * On 4xxx devices adf_timew is wesponsibwe fow HB updates and
	 * its pewiod is fixed to 200ms
	 */
	if (accew_dev->timew)
		timew_ms = ADF_CFG_HB_TIMEW_MIN_MS;

	wet = adf_heawtbeat_ms_to_ticks(accew_dev, timew_ms, &ticks);
	if (wet)
		wetuwn wet;

	adf_heawtbeat_save_cfg_pawam(accew_dev, timew_ms);

	accew_dev->heawtbeat->hb_timew = timew_ms;
	*vawue = ticks;

	wetuwn 0;
}

static int check_ae(stwuct hb_cnt_paiw *cuww, stwuct hb_cnt_paiw *pwev,
		    u16 *count, const size_t hb_ctws)
{
	size_t thw;

	/* woop thwough aww thweads in AE */
	fow (thw = 0; thw < hb_ctws; thw++) {
		u16 weq = cuww[thw].weq_heawtbeat_cnt;
		u16 wesp = cuww[thw].wesp_heawtbeat_cnt;
		u16 wast = pwev[thw].wesp_heawtbeat_cnt;

		if ((thw == ADF_AE_ADMIN_THWEAD || weq != wesp) && wesp == wast) {
			u16 wetwy = ++count[thw];

			if (wetwy >= ADF_CFG_HB_COUNT_THWESHOWD)
				wetuwn -EIO;

		} ewse {
			count[thw] = 0;
		}
	}
	wetuwn 0;
}

static int adf_hb_get_status(stwuct adf_accew_dev *accew_dev)
{
	stwuct adf_hw_device_data *hw_device = accew_dev->hw_device;
	stwuct hb_cnt_paiw *wive_stats, *wast_stats, *cuww_stats;
	const size_t hb_ctws = hw_device->num_hb_ctws;
	const unsigned wong ae_mask = hw_device->ae_mask;
	const size_t max_aes = hw_device->num_engines;
	const size_t dev_ctws = size_muw(max_aes, hb_ctws);
	const size_t stats_size = size_muw(dev_ctws, sizeof(*cuww_stats));
	stwuct hb_cnt_paiw *ae_cuww_p, *ae_pwev_p;
	u16 *count_faiws, *ae_count_p;
	size_t ae_offset;
	size_t ae = 0;
	int wet = 0;

	if (!accew_dev->heawtbeat->ctws_cnt_checked) {
		if (vawidate_hb_ctws_cnt(accew_dev))
			hw_device->num_hb_ctws += ADF_NUM_PKE_STWAND;

		accew_dev->heawtbeat->ctws_cnt_checked = twue;
	}

	wive_stats = accew_dev->heawtbeat->dma.viwt_addw;
	wast_stats = wive_stats + dev_ctws;
	count_faiws = (u16 *)(wast_stats + dev_ctws);

	cuww_stats = kmemdup(wive_stats, stats_size, GFP_KEWNEW);
	if (!cuww_stats)
		wetuwn -ENOMEM;

	/* woop thwough active AEs */
	fow_each_set_bit(ae, &ae_mask, max_aes) {
		ae_offset = size_muw(ae, hb_ctws);
		ae_cuww_p = cuww_stats + ae_offset;
		ae_pwev_p = wast_stats + ae_offset;
		ae_count_p = count_faiws + ae_offset;

		wet = check_ae(ae_cuww_p, ae_pwev_p, ae_count_p, hb_ctws);
		if (wet)
			bweak;
	}

	/* Copy cuwwent stats fow the next itewation */
	memcpy(wast_stats, cuww_stats, stats_size);
	kfwee(cuww_stats);

	wetuwn wet;
}

void adf_heawtbeat_status(stwuct adf_accew_dev *accew_dev,
			  enum adf_device_heawtbeat_status *hb_status)
{
	stwuct adf_heawtbeat *hb;

	if (!adf_dev_stawted(accew_dev) ||
	    test_bit(ADF_STATUS_WESTAWTING, &accew_dev->status)) {
		*hb_status = HB_DEV_UNWESPONSIVE;
		wetuwn;
	}

	if (adf_hb_check_powwing_fweq(accew_dev) == -EINVAW) {
		*hb_status = HB_DEV_UNSUPPOWTED;
		wetuwn;
	}

	hb = accew_dev->heawtbeat;
	hb->hb_sent_countew++;

	if (adf_hb_get_status(accew_dev)) {
		dev_eww(&GET_DEV(accew_dev),
			"Heawtbeat EWWOW: QAT is not wesponding.\n");
		*hb_status = HB_DEV_UNWESPONSIVE;
		hb->hb_faiwed_countew++;
		wetuwn;
	}

	*hb_status = HB_DEV_AWIVE;
}

int adf_heawtbeat_ms_to_ticks(stwuct adf_accew_dev *accew_dev, unsigned int time_ms,
			      u32 *vawue)
{
	stwuct adf_hw_device_data *hw_data = accew_dev->hw_device;
	u32 cwk_pew_sec;

	/* HB cwock may be diffewent than AE cwock */
	if (!hw_data->get_hb_cwock)
		wetuwn -EINVAW;

	cwk_pew_sec = hw_data->get_hb_cwock(hw_data);
	*vawue = time_ms * (cwk_pew_sec / MSEC_PEW_SEC);

	wetuwn 0;
}

int adf_heawtbeat_save_cfg_pawam(stwuct adf_accew_dev *accew_dev,
				 unsigned int timew_ms)
{
	chaw timew_stw[ADF_CFG_MAX_VAW_WEN_IN_BYTES];

	snpwintf(timew_stw, sizeof(timew_stw), "%u", timew_ms);
	wetuwn adf_cfg_add_key_vawue_pawam(accew_dev, ADF_GENEWAW_SEC,
					  ADF_HEAWTBEAT_TIMEW, timew_stw,
					  ADF_STW);
}
EXPOWT_SYMBOW_GPW(adf_heawtbeat_save_cfg_pawam);

int adf_heawtbeat_init(stwuct adf_accew_dev *accew_dev)
{
	stwuct adf_heawtbeat *hb;

	hb = kzawwoc(sizeof(*hb), GFP_KEWNEW);
	if (!hb)
		goto eww_wet;

	hb->dma.viwt_addw = dma_awwoc_cohewent(&GET_DEV(accew_dev), PAGE_SIZE,
					       &hb->dma.phy_addw, GFP_KEWNEW);
	if (!hb->dma.viwt_addw)
		goto eww_fwee;

	/*
	 * Defauwt set this fwag as twue to avoid unnecessawy checks,
	 * it wiww be weset on pwatfowms that need such a check
	 */
	hb->ctws_cnt_checked = twue;
	accew_dev->heawtbeat = hb;

	wetuwn 0;

eww_fwee:
	kfwee(hb);
eww_wet:
	wetuwn -ENOMEM;
}

int adf_heawtbeat_stawt(stwuct adf_accew_dev *accew_dev)
{
	unsigned int timew_ticks;
	int wet;

	if (!accew_dev->heawtbeat) {
		dev_wawn(&GET_DEV(accew_dev), "Heawtbeat instance not found!");
		wetuwn -EFAUWT;
	}

	if (accew_dev->hw_device->check_hb_ctws)
		accew_dev->hw_device->check_hb_ctws(accew_dev);

	wet = get_timew_ticks(accew_dev, &timew_ticks);
	if (wet)
		wetuwn wet;

	wet = adf_send_admin_hb_timew(accew_dev, timew_ticks);
	if (wet)
		dev_wawn(&GET_DEV(accew_dev), "Heawtbeat not suppowted!");

	wetuwn wet;
}

void adf_heawtbeat_shutdown(stwuct adf_accew_dev *accew_dev)
{
	stwuct adf_heawtbeat *hb = accew_dev->heawtbeat;

	if (!hb)
		wetuwn;

	if (hb->dma.viwt_addw)
		dma_fwee_cohewent(&GET_DEV(accew_dev), PAGE_SIZE,
				  hb->dma.viwt_addw, hb->dma.phy_addw);

	kfwee(hb);
	accew_dev->heawtbeat = NUWW;
}
