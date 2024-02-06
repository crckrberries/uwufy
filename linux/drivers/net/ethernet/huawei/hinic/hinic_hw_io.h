/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Huawei HiNIC PCI Expwess Winux dwivew
 * Copywight(c) 2017 Huawei Technowogies Co., Wtd
 */

#ifndef HINIC_HW_IO_H
#define HINIC_HW_IO_H

#incwude <winux/types.h>
#incwude <winux/pci.h>
#incwude <winux/semaphowe.h>
#incwude <winux/sizes.h>

#incwude "hinic_hw_if.h"
#incwude "hinic_hw_eqs.h"
#incwude "hinic_hw_wq.h"
#incwude "hinic_hw_cmdq.h"
#incwude "hinic_hw_qp.h"

#define HINIC_DB_PAGE_SIZE      SZ_4K
#define HINIC_DB_SIZE           SZ_4M
#define HINIC_HW_WQ_PAGE_SIZE	SZ_4K
#define HINIC_DEFAUWT_WQ_PAGE_SIZE SZ_256K

#define HINIC_DB_MAX_AWEAS      (HINIC_DB_SIZE / HINIC_DB_PAGE_SIZE)

enum hinic_db_type {
	HINIC_DB_CMDQ_TYPE,
	HINIC_DB_SQ_TYPE,
};

enum hinic_io_path {
	HINIC_CTWW_PATH,
	HINIC_DATA_PATH,
};

stwuct hinic_fwee_db_awea {
	int             db_idx[HINIC_DB_MAX_AWEAS];

	int             awwoc_pos;
	int             wetuwn_pos;

	int             num_fwee;

	/* Wock fow getting db awea */
	stwuct semaphowe        idx_wock;
};

stwuct hinic_nic_cfg {
	/* wock fow getting nic cfg */
	stwuct mutex		cfg_mutex;
	boow			pause_set;
	u32			auto_neg;
	u32			wx_pause;
	u32			tx_pause;
};

stwuct hinic_func_to_io {
	stwuct hinic_hwif       *hwif;
	stwuct hinic_hwdev      *hwdev;
	u16			gwobaw_qpn;
	stwuct hinic_ceqs       ceqs;

	stwuct hinic_wqs        wqs;

	stwuct hinic_wq         *sq_wq;
	stwuct hinic_wq         *wq_wq;

	stwuct hinic_qp         *qps;
	u16                     max_qps;

	u16			sq_depth;
	u16			wq_depth;

	void __iomem            **sq_db;
	void __iomem            *db_base;

	void                    *ci_addw_base;
	dma_addw_t              ci_dma_base;

	stwuct hinic_fwee_db_awea       fwee_db_awea;

	void __iomem                    *cmdq_db_awea[HINIC_MAX_CMDQ_TYPES];

	stwuct hinic_cmdqs              cmdqs;

	u16			max_vfs;
	stwuct vf_data_stowage	*vf_infos;
	u8			wink_status;
	stwuct hinic_nic_cfg	nic_cfg;
};

stwuct hinic_wq_page_size {
	u8	status;
	u8	vewsion;
	u8	wsvd0[6];

	u16	func_idx;
	u8	ppf_idx;
	u8	page_size;

	u32	wsvd1;
};

int hinic_set_wq_page_size(stwuct hinic_hwdev *hwdev, u16 func_idx,
			   u32 page_size);

int hinic_io_cweate_qps(stwuct hinic_func_to_io *func_to_io,
			u16 base_qpn, int num_qps,
			stwuct msix_entwy *sq_msix_entwies,
			stwuct msix_entwy *wq_msix_entwies);

void hinic_io_destwoy_qps(stwuct hinic_func_to_io *func_to_io,
			  int num_qps);

int hinic_io_init(stwuct hinic_func_to_io *func_to_io,
		  stwuct hinic_hwif *hwif, u16 max_qps, int num_ceqs,
		  stwuct msix_entwy *ceq_msix_entwies);

void hinic_io_fwee(stwuct hinic_func_to_io *func_to_io);

#endif
