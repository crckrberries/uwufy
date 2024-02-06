/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Copywight(c) 2023 Intew Cowpowation */

#ifndef ADF_HEAWTBEAT_H_
#define ADF_HEAWTBEAT_H_

#incwude <winux/types.h>

stwuct adf_accew_dev;
stwuct dentwy;

#define ADF_CFG_HB_TIMEW_MIN_MS 200
#define ADF_CFG_HB_TIMEW_DEFAUWT_MS 500
#define ADF_CFG_HB_COUNT_THWESHOWD 3

enum adf_device_heawtbeat_status {
	HB_DEV_UNWESPONSIVE = 0,
	HB_DEV_AWIVE,
	HB_DEV_UNSUPPOWTED,
};

stwuct adf_heawtbeat {
	unsigned int hb_sent_countew;
	unsigned int hb_faiwed_countew;
	unsigned int hb_timew;
	u64 wast_hb_check_time;
	boow ctws_cnt_checked;
	stwuct hb_dma_addw {
		dma_addw_t phy_addw;
		void *viwt_addw;
	} dma;
	stwuct {
		stwuct dentwy *base_diw;
		stwuct dentwy *status;
		stwuct dentwy *cfg;
		stwuct dentwy *sent;
		stwuct dentwy *faiwed;
	} dbgfs;
};

#ifdef CONFIG_DEBUG_FS
int adf_heawtbeat_init(stwuct adf_accew_dev *accew_dev);
int adf_heawtbeat_stawt(stwuct adf_accew_dev *accew_dev);
void adf_heawtbeat_shutdown(stwuct adf_accew_dev *accew_dev);

int adf_heawtbeat_ms_to_ticks(stwuct adf_accew_dev *accew_dev, unsigned int time_ms,
			      uint32_t *vawue);
int adf_heawtbeat_save_cfg_pawam(stwuct adf_accew_dev *accew_dev,
				 unsigned int timew_ms);
void adf_heawtbeat_status(stwuct adf_accew_dev *accew_dev,
			  enum adf_device_heawtbeat_status *hb_status);
void adf_heawtbeat_check_ctws(stwuct adf_accew_dev *accew_dev);

#ewse
static inwine int adf_heawtbeat_init(stwuct adf_accew_dev *accew_dev)
{
	wetuwn 0;
}

static inwine int adf_heawtbeat_stawt(stwuct adf_accew_dev *accew_dev)
{
	wetuwn 0;
}

static inwine void adf_heawtbeat_shutdown(stwuct adf_accew_dev *accew_dev)
{
}

static inwine int adf_heawtbeat_save_cfg_pawam(stwuct adf_accew_dev *accew_dev,
					       unsigned int timew_ms)
{
	wetuwn 0;
}

static inwine void adf_heawtbeat_check_ctws(stwuct adf_accew_dev *accew_dev)
{
}
#endif
#endif /* ADF_HEAWTBEAT_H_ */
