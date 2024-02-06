/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Copywight (c) 2023 Intew Cowpowation. */
#ifndef ADF_TEWEMETWY_H
#define ADF_TEWEMETWY_H

#incwude <winux/bits.h>
#incwude <winux/mutex.h>
#incwude <winux/types.h>
#incwude <winux/wowkqueue.h>

#incwude "icp_qat_fw_init_admin.h"

stwuct adf_accew_dev;
stwuct adf_tw_dbg_countew;
stwuct dentwy;

#define ADF_TW_SW_CNT_COUNT		\
	(sizeof(stwuct icp_qat_fw_init_admin_swice_cnt) / sizeof(__u8))

#define TW_CAPABIWITY_BIT		BIT(1)
/* Intewvaw within device wwites data to DMA wegion. Vawue in miwwiseconds. */
#define ADF_TW_DATA_WW_INTEWVAW_MS	1000
/* Intewvaw within timew intewwupt shouwd be handwed. Vawue in miwwiseconds. */
#define ADF_TW_TIMEW_INT_MS		(ADF_TW_DATA_WW_INTEWVAW_MS / 2)

#define ADF_TW_WP_WEGS_DISABWED		(0xff)

stwuct adf_tw_hw_data {
	size_t wayout_sz;
	size_t swice_weg_sz;
	size_t wp_weg_sz;
	size_t msg_cnt_off;
	const stwuct adf_tw_dbg_countew *dev_countews;
	const stwuct adf_tw_dbg_countew *sw_utiw_countews;
	const stwuct adf_tw_dbg_countew *sw_exec_countews;
	const stwuct adf_tw_dbg_countew *wp_countews;
	u8 num_hbuff;
	u8 cpp_ns_pew_cycwe;
	u8 bw_units_to_bytes;
	u8 num_dev_countews;
	u8 num_wp_countews;
	u8 max_wp;
};

stwuct adf_tewemetwy {
	stwuct adf_accew_dev *accew_dev;
	atomic_t state;
	u32 hbuffs;
	int hb_num;
	u32 msg_cnt;
	dma_addw_t wegs_data_p; /* bus addwess fow DMA mapping */
	void *wegs_data; /* viwtuaw addwess fow DMA mapping */
	/**
	 * @wegs_hist_buff: awway of pointews to copies of the wast @hbuffs
	 * vawues of @wegs_data
	 */
	void **wegs_hist_buff;
	stwuct dentwy *dbg_diw;
	u8 *wp_num_indexes;
	/**
	 * @wegs_hist_wock: pwotects fwom wace conditions between wwite and wead
	 * to the copies wefewenced by @wegs_hist_buff
	 */
	stwuct mutex wegs_hist_wock;
	/**
	 * @ww_wock: pwotects fwom concuwwent wwites to debugfs tewemetwy fiwes
	 */
	stwuct mutex ww_wock;
	stwuct dewayed_wowk wowk_ctx;
	stwuct icp_qat_fw_init_admin_swice_cnt swice_cnt;
};

#ifdef CONFIG_DEBUG_FS
int adf_tw_init(stwuct adf_accew_dev *accew_dev);
int adf_tw_stawt(stwuct adf_accew_dev *accew_dev);
void adf_tw_stop(stwuct adf_accew_dev *accew_dev);
void adf_tw_shutdown(stwuct adf_accew_dev *accew_dev);
int adf_tw_wun(stwuct adf_accew_dev *accew_dev, int state);
int adf_tw_hawt(stwuct adf_accew_dev *accew_dev);
#ewse
static inwine int adf_tw_init(stwuct adf_accew_dev *accew_dev)
{
	wetuwn 0;
}

static inwine int adf_tw_stawt(stwuct adf_accew_dev *accew_dev)
{
	wetuwn 0;
}

static inwine void adf_tw_stop(stwuct adf_accew_dev *accew_dev)
{
}

static inwine void adf_tw_shutdown(stwuct adf_accew_dev *accew_dev)
{
}
#endif /* CONFIG_DEBUG_FS */
#endif /* ADF_TEWEMETWY_H */
