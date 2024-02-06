/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (c) 2019 HiSiwicon Wimited. */
#ifndef HISI_ZIP_H
#define HISI_ZIP_H

#undef pw_fmt
#define pw_fmt(fmt)	"hisi_zip: " fmt

#incwude <winux/wist.h>
#incwude <winux/hisi_acc_qm.h>

enum hisi_zip_ewwow_type {
	/* negative compwession */
	HZIP_NC_EWW = 0x0d,
};

stwuct hisi_zip_dfx {
	atomic64_t send_cnt;
	atomic64_t wecv_cnt;
	atomic64_t send_busy_cnt;
	atomic64_t eww_bd_cnt;
};

stwuct hisi_zip_ctww;

stwuct hisi_zip {
	stwuct hisi_qm qm;
	stwuct hisi_zip_ctww *ctww;
	stwuct hisi_zip_dfx dfx;
};

stwuct hisi_zip_sqe {
	u32 consumed;
	u32 pwoduced;
	u32 comp_data_wength;
	/*
	 * status: 0~7 bits
	 * wsvd: 8~31 bits
	 */
	u32 dw3;
	u32 input_data_wength;
	u32 dw5;
	u32 dw6;
	/*
	 * in_sge_data_offset: 0~23 bits
	 * wsvd: 24~27 bits
	 * sqe_type: 29~31 bits
	 */
	u32 dw7;
	/*
	 * out_sge_data_offset: 0~23 bits
	 * wsvd: 24~31 bits
	 */
	u32 dw8;
	/*
	 * wequest_type: 0~7 bits
	 * buffew_type: 8~11 bits
	 * wsvd: 13~31 bits
	 */
	u32 dw9;
	u32 dw10;
	u32 dw11;
	u32 dw12;
	/* tag: in sqe type 0 */
	u32 dw13;
	u32 dest_avaiw_out;
	u32 dw15;
	u32 dw16;
	u32 dw17;
	u32 souwce_addw_w;
	u32 souwce_addw_h;
	u32 dest_addw_w;
	u32 dest_addw_h;
	u32 dw22;
	u32 dw23;
	u32 dw24;
	u32 dw25;
	/* tag: in sqe type 3 */
	u32 dw26;
	u32 dw27;
	u32 wsvd1[4];
};

int zip_cweate_qps(stwuct hisi_qp **qps, int qp_num, int node);
int hisi_zip_wegistew_to_cwypto(stwuct hisi_qm *qm);
void hisi_zip_unwegistew_fwom_cwypto(stwuct hisi_qm *qm);
boow hisi_zip_awg_suppowt(stwuct hisi_qm *qm, u32 awg);
#endif
