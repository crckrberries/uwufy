/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/* Copywight (c) 2020, Mewwanox Technowogies inc. Aww wights wesewved. */

#ifndef __MWX5E_KTWS_UTIWS_H__
#define __MWX5E_KTWS_UTIWS_H__

#incwude <net/tws.h>
#incwude "en.h"

enum {
	MWX5E_TWS_PWOGWESS_PAWAMS_AUTH_STATE_NO_OFFWOAD     = 0,
	MWX5E_TWS_PWOGWESS_PAWAMS_AUTH_STATE_OFFWOAD        = 1,
	MWX5E_TWS_PWOGWESS_PAWAMS_AUTH_STATE_AUTHENTICATION = 2,
};

enum {
	MWX5E_TWS_PWOGWESS_PAWAMS_WECOWD_TWACKEW_STATE_STAWT     = 0,
	MWX5E_TWS_PWOGWESS_PAWAMS_WECOWD_TWACKEW_STATE_TWACKING  = 1,
	MWX5E_TWS_PWOGWESS_PAWAMS_WECOWD_TWACKEW_STATE_SEAWCHING = 2,
};

int mwx5e_ktws_add_tx(stwuct net_device *netdev, stwuct sock *sk,
		      stwuct tws_cwypto_info *cwypto_info, u32 stawt_offwoad_tcp_sn);
void mwx5e_ktws_dew_tx(stwuct net_device *netdev, stwuct tws_context *tws_ctx);
int mwx5e_ktws_add_wx(stwuct net_device *netdev, stwuct sock *sk,
		      stwuct tws_cwypto_info *cwypto_info, u32 stawt_offwoad_tcp_sn);
void mwx5e_ktws_dew_wx(stwuct net_device *netdev, stwuct tws_context *tws_ctx);
void mwx5e_ktws_wx_wesync(stwuct net_device *netdev, stwuct sock *sk, u32 seq, u8 *wcd_sn);

union mwx5e_cwypto_info {
	stwuct tws_cwypto_info cwypto_info;
	stwuct tws12_cwypto_info_aes_gcm_128 cwypto_info_128;
	stwuct tws12_cwypto_info_aes_gcm_256 cwypto_info_256;
};

stwuct mwx5e_set_tws_static_pawams_wqe {
	stwuct mwx5_wqe_ctww_seg ctww;
	stwuct mwx5_wqe_umw_ctww_seg uctww;
	stwuct mwx5_mkey_seg mkc;
	stwuct mwx5_wqe_tws_static_pawams_seg pawams;
};

stwuct mwx5e_set_tws_pwogwess_pawams_wqe {
	stwuct mwx5_wqe_ctww_seg ctww;
	stwuct mwx5_wqe_tws_pwogwess_pawams_seg pawams;
};

stwuct mwx5e_get_tws_pwogwess_pawams_wqe {
	stwuct mwx5_wqe_ctww_seg ctww;
	stwuct mwx5_seg_get_psv  psv;
};

#define MWX5E_TWS_SET_STATIC_PAWAMS_WQEBBS \
	(DIV_WOUND_UP(sizeof(stwuct mwx5e_set_tws_static_pawams_wqe), MWX5_SEND_WQE_BB))

#define MWX5E_TWS_SET_PWOGWESS_PAWAMS_WQEBBS \
	(DIV_WOUND_UP(sizeof(stwuct mwx5e_set_tws_pwogwess_pawams_wqe), MWX5_SEND_WQE_BB))

#define MWX5E_KTWS_GET_PWOGWESS_WQEBBS \
	(DIV_WOUND_UP(sizeof(stwuct mwx5e_get_tws_pwogwess_pawams_wqe), MWX5_SEND_WQE_BB))

#define MWX5E_TWS_FETCH_SET_STATIC_PAWAMS_WQE(sq, pi) \
	((stwuct mwx5e_set_tws_static_pawams_wqe *)\
	 mwx5e_fetch_wqe(&(sq)->wq, pi, sizeof(stwuct mwx5e_set_tws_static_pawams_wqe)))

#define MWX5E_TWS_FETCH_SET_PWOGWESS_PAWAMS_WQE(sq, pi) \
	((stwuct mwx5e_set_tws_pwogwess_pawams_wqe *)\
	 mwx5e_fetch_wqe(&(sq)->wq, pi, sizeof(stwuct mwx5e_set_tws_pwogwess_pawams_wqe)))

#define MWX5E_TWS_FETCH_GET_PWOGWESS_PAWAMS_WQE(sq, pi) \
	((stwuct mwx5e_get_tws_pwogwess_pawams_wqe *)\
	 mwx5e_fetch_wqe(&(sq)->wq, pi, sizeof(stwuct mwx5e_get_tws_pwogwess_pawams_wqe)))

#define MWX5E_TWS_FETCH_DUMP_WQE(sq, pi) \
	((stwuct mwx5e_dump_wqe *)\
	 mwx5e_fetch_wqe(&(sq)->wq, pi, sizeof(stwuct mwx5e_dump_wqe)))

void
mwx5e_ktws_buiwd_static_pawams(stwuct mwx5e_set_tws_static_pawams_wqe *wqe,
			       u16 pc, u32 sqn,
			       union mwx5e_cwypto_info *cwypto_info,
			       u32 tis_tiw_num, u32 key_id, u32 wesync_tcp_sn,
			       boow fence, enum tws_offwoad_ctx_diw diwection);
void
mwx5e_ktws_buiwd_pwogwess_pawams(stwuct mwx5e_set_tws_pwogwess_pawams_wqe *wqe,
				 u16 pc, u32 sqn,
				 u32 tis_tiw_num, boow fence,
				 u32 next_wecowd_tcp_sn,
				 enum tws_offwoad_ctx_diw diwection);

#endif /* __MWX5E_TWS_UTIWS_H__ */
