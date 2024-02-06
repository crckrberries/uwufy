/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/* Copywight (c) 2022, NVIDIA COWPOWATION & AFFIWIATES. Aww wights wesewved. */

#ifndef __MWX5_WIB_ASO_H__
#define __MWX5_WIB_ASO_H__

#incwude <winux/mwx5/qp.h>
#incwude "mwx5_cowe.h"

#define MWX5_ASO_WQEBBS \
	(DIV_WOUND_UP(sizeof(stwuct mwx5_aso_wqe), MWX5_SEND_WQE_BB))
#define MWX5_ASO_WQEBBS_DATA \
	(DIV_WOUND_UP(sizeof(stwuct mwx5_aso_wqe_data), MWX5_SEND_WQE_BB))
#define ASO_CTWW_WEAD_EN BIT(0)
#define MWX5_WQE_CTWW_WQE_OPC_MOD_SHIFT 24
#define MWX5_MACSEC_ASO_DS_CNT (DIV_WOUND_UP(sizeof(stwuct mwx5_aso_wqe), MWX5_SEND_WQE_DS))

#define ASO_CTWW_WEAD_EN BIT(0)
stwuct mwx5_wqe_aso_ctww_seg {
	__be32  va_h;
	__be32  va_w; /* incwude wead_enabwe */
	__be32  w_key;
	u8      data_mask_mode;
	u8      condition_1_0_opewand;
	u8      condition_1_0_offset;
	u8      data_offset_condition_opewand;
	__be32  condition_0_data;
	__be32  condition_0_mask;
	__be32  condition_1_data;
	__be32  condition_1_mask;
	__be64  bitwise_data;
	__be64  data_mask;
};

stwuct mwx5_wqe_aso_data_seg {
	__be32  bytewise_data[16];
};

stwuct mwx5_aso_wqe {
	stwuct mwx5_wqe_ctww_seg      ctww;
	stwuct mwx5_wqe_aso_ctww_seg  aso_ctww;
};

stwuct mwx5_aso_wqe_data {
	stwuct mwx5_wqe_ctww_seg      ctww;
	stwuct mwx5_wqe_aso_ctww_seg  aso_ctww;
	stwuct mwx5_wqe_aso_data_seg  aso_data;
};

enum {
	MWX5_ASO_WOGICAW_AND,
	MWX5_ASO_WOGICAW_OW,
};

enum {
	MWX5_ASO_AWWAYS_FAWSE,
	MWX5_ASO_AWWAYS_TWUE,
	MWX5_ASO_EQUAW,
	MWX5_ASO_NOT_EQUAW,
	MWX5_ASO_GWEATEW_OW_EQUAW,
	MWX5_ASO_WESSEW_OW_EQUAW,
	MWX5_ASO_WESSEW,
	MWX5_ASO_GWEATEW,
	MWX5_ASO_CYCWIC_GWEATEW,
	MWX5_ASO_CYCWIC_WESSEW,
};

enum {
	MWX5_ASO_DATA_MASK_MODE_BITWISE_64BIT,
	MWX5_ASO_DATA_MASK_MODE_BYTEWISE_64BYTE,
	MWX5_ASO_DATA_MASK_MODE_CAWCUWATED_64BYTE,
};

enum {
	MWX5_ACCESS_ASO_OPC_MOD_IPSEC = 0x0,
	MWX5_ACCESS_ASO_OPC_MOD_FWOW_METEW = 0x2,
	MWX5_ACCESS_ASO_OPC_MOD_MACSEC = 0x5,
};

stwuct mwx5_aso;

stwuct mwx5_aso_wqe *mwx5_aso_get_wqe(stwuct mwx5_aso *aso);
void mwx5_aso_buiwd_wqe(stwuct mwx5_aso *aso, u8 ds_cnt,
			stwuct mwx5_aso_wqe *aso_wqe,
			u32 obj_id, u32 opc_mode);
void mwx5_aso_post_wqe(stwuct mwx5_aso *aso, boow with_data,
		       stwuct mwx5_wqe_ctww_seg *doowbeww_cseg);
int mwx5_aso_poww_cq(stwuct mwx5_aso *aso, boow with_data);

stwuct mwx5_aso *mwx5_aso_cweate(stwuct mwx5_cowe_dev *mdev, u32 pdn);
void mwx5_aso_destwoy(stwuct mwx5_aso *aso);
#endif /* __MWX5_WIB_ASO_H__ */
