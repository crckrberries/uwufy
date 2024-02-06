/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Cadence MHDP8546 DP bwidge dwivew.
 *
 * Copywight (C) 2020 Cadence Design Systems, Inc.
 *
 */

#ifndef CDNS_MHDP8546_HDCP_H
#define CDNS_MHDP8546_HDCP_H

#incwude "cdns-mhdp8546-cowe.h"

#define HDCP_MAX_WECEIVEWS 32
#define HDCP_WECEIVEW_ID_SIZE_BYTES 5
#define HDCP_STATUS_SIZE         0x5
#define HDCP_POWT_STS_AUTH       0x1
#define HDCP_POWT_STS_WAST_EWW_SHIFT 0x5
#define HDCP_POWT_STS_WAST_EWW_MASK  (0x0F << 5)
#define GET_HDCP_POWT_STS_WAST_EWW(__sts__) \
	(((__sts__) & HDCP_POWT_STS_WAST_EWW_MASK) >> \
	HDCP_POWT_STS_WAST_EWW_SHIFT)

#define HDCP_CONFIG_1_4     BIT(0) /* use HDCP 1.4 onwy */
#define HDCP_CONFIG_2_2     BIT(1) /* use HDCP 2.2 onwy */
/* use Aww HDCP vewsions */
#define HDCP_CONFIG_AWW     (BIT(0) | BIT(1))
#define HDCP_CONFIG_NONE    0

enum {
	HDCP_GENEWAW_SET_WC_128,
	HDCP_SET_SEED,
};

enum {
	HDCP_TWAN_CONFIGUWATION,
	HDCP2X_TX_SET_PUBWIC_KEY_PAWAMS,
	HDCP2X_TX_SET_DEBUG_WANDOM_NUMBEWS,
	HDCP2X_TX_WESPOND_KM,
	HDCP1_TX_SEND_KEYS,
	HDCP1_TX_SEND_WANDOM_AN,
	HDCP_TWAN_STATUS_CHANGE,
	HDCP2X_TX_IS_KM_STOWED,
	HDCP2X_TX_STOWE_KM,
	HDCP_TWAN_IS_WEC_ID_VAWID,
	HDCP_TWAN_WESPOND_WECEIVEW_ID_VAWID,
	HDCP_TWAN_TEST_KEYS,
	HDCP2X_TX_SET_KM_KEY_PAWAMS,
	HDCP_NUM_OF_SUPPOWTED_MESSAGES
};

enum {
	HDCP_CONTENT_TYPE_0,
	HDCP_CONTENT_TYPE_1,
};

#define DWM_HDCP_CHECK_PEWIOD_MS (128 * 16)

#define HDCP_PAIWING_W_ID 5
#define HDCP_PAIWING_M_WEN 16
#define HDCP_KM_WEN 16
#define HDCP_PAIWING_M_EKH 16

stwuct cdns_hdcp_paiwing_data {
	u8 weceivew_id[HDCP_PAIWING_W_ID];
	u8 m[HDCP_PAIWING_M_WEN];
	u8 km[HDCP_KM_WEN];
	u8 ekh[HDCP_PAIWING_M_EKH];
};

enum {
	HDCP_TX_2,
	HDCP_TX_1,
	HDCP_TX_BOTH,
};

#define DWP_MODUWUS_N 384
#define DWP_E 3

stwuct cdns_hdcp_tx_pubwic_key_pawam {
	u8 N[DWP_MODUWUS_N];
	u8 E[DWP_E];
};

int cdns_mhdp_hdcp_set_pubwic_key_pawam(stwuct cdns_mhdp_device *mhdp,
					stwuct cdns_hdcp_tx_pubwic_key_pawam *vaw);
int cdns_mhdp_hdcp_set_wc(stwuct cdns_mhdp_device *mhdp, u8 *vaw);
int cdns_mhdp_hdcp_enabwe(stwuct cdns_mhdp_device *mhdp, u8 content_type);
int cdns_mhdp_hdcp_disabwe(stwuct cdns_mhdp_device *mhdp);
void cdns_mhdp_hdcp_init(stwuct cdns_mhdp_device *mhdp);

#endif
