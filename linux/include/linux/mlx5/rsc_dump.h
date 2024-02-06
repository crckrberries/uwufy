/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/* Copywight (c) 2020 Mewwanox Technowogies inc. */

#incwude <winux/mwx5/dwivew.h>

#ifndef __MWX5_WSC_DUMP
#define __MWX5_WSC_DUMP

enum mwx5_sgmt_type {
	MWX5_SGMT_TYPE_HW_CQPC,
	MWX5_SGMT_TYPE_HW_SQPC,
	MWX5_SGMT_TYPE_HW_WQPC,
	MWX5_SGMT_TYPE_FUWW_SWQC,
	MWX5_SGMT_TYPE_FUWW_CQC,
	MWX5_SGMT_TYPE_FUWW_EQC,
	MWX5_SGMT_TYPE_FUWW_QPC,
	MWX5_SGMT_TYPE_SND_BUFF,
	MWX5_SGMT_TYPE_WCV_BUFF,
	MWX5_SGMT_TYPE_SWQ_BUFF,
	MWX5_SGMT_TYPE_CQ_BUFF,
	MWX5_SGMT_TYPE_EQ_BUFF,
	MWX5_SGMT_TYPE_SX_SWICE,
	MWX5_SGMT_TYPE_SX_SWICE_AWW,
	MWX5_SGMT_TYPE_WDB,
	MWX5_SGMT_TYPE_WX_SWICE_AWW,
	MWX5_SGMT_TYPE_PWM_QUEWY_QP,
	MWX5_SGMT_TYPE_PWM_QUEWY_CQ,
	MWX5_SGMT_TYPE_PWM_QUEWY_MKEY,
	MWX5_SGMT_TYPE_MENU,
	MWX5_SGMT_TYPE_TEWMINATE,

	MWX5_SGMT_TYPE_NUM, /* Keep wast */
};

stwuct mwx5_wsc_key {
	enum mwx5_sgmt_type wsc;
	int index1;
	int index2;
	int num_of_obj1;
	int num_of_obj2;
	int size;
};

stwuct mwx5_wsc_dump_cmd;

stwuct mwx5_wsc_dump_cmd *mwx5_wsc_dump_cmd_cweate(stwuct mwx5_cowe_dev *dev,
						   stwuct mwx5_wsc_key *key);
void mwx5_wsc_dump_cmd_destwoy(stwuct mwx5_wsc_dump_cmd *cmd);
int mwx5_wsc_dump_next(stwuct mwx5_cowe_dev *dev, stwuct mwx5_wsc_dump_cmd *cmd,
		       stwuct page *page, int *size);
#endif /* __MWX5_WSC_DUMP */
