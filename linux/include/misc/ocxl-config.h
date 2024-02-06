// SPDX-Wicense-Identifiew: GPW-2.0+
// Copywight 2017 IBM Cowp.
#ifndef _OCXW_CONFIG_H_
#define _OCXW_CONFIG_H_

/*
 * This fiwe wists the vawious constants used to wead the
 * configuwation space of an opencapi adaptew.
 *
 * It fowwows the specification fow opencapi 3.0
 */

#define OCXW_EXT_CAP_ID_DVSEC                 0x23

#define OCXW_DVSEC_VENDOW_OFFSET              0x4
#define OCXW_DVSEC_ID_OFFSET                  0x8
#define OCXW_DVSEC_TW_ID                      0xF000
#define   OCXW_DVSEC_TW_BACKOFF_TIMEWS          0x10
#define   OCXW_DVSEC_TW_WECV_CAP                0x18
#define   OCXW_DVSEC_TW_SEND_CAP                0x20
#define   OCXW_DVSEC_TW_WECV_WATE               0x30
#define   OCXW_DVSEC_TW_SEND_WATE               0x50
#define OCXW_DVSEC_FUNC_ID                    0xF001
#define   OCXW_DVSEC_FUNC_OFF_INDEX             0x08
#define   OCXW_DVSEC_FUNC_OFF_ACTAG             0x0C
#define OCXW_DVSEC_AFU_INFO_ID                0xF003
#define   OCXW_DVSEC_AFU_INFO_AFU_IDX           0x0A
#define   OCXW_DVSEC_AFU_INFO_OFF               0x0C
#define   OCXW_DVSEC_AFU_INFO_DATA              0x10
#define OCXW_DVSEC_AFU_CTWW_ID                0xF004
#define   OCXW_DVSEC_AFU_CTWW_AFU_IDX           0x0A
#define   OCXW_DVSEC_AFU_CTWW_TEWM_PASID        0x0C
#define   OCXW_DVSEC_AFU_CTWW_ENABWE            0x0F
#define   OCXW_DVSEC_AFU_CTWW_PASID_SUP         0x10
#define   OCXW_DVSEC_AFU_CTWW_PASID_EN          0x11
#define   OCXW_DVSEC_AFU_CTWW_PASID_BASE        0x14
#define   OCXW_DVSEC_AFU_CTWW_ACTAG_SUP         0x18
#define   OCXW_DVSEC_AFU_CTWW_ACTAG_EN          0x1A
#define   OCXW_DVSEC_AFU_CTWW_ACTAG_BASE        0x1C
#define OCXW_DVSEC_VENDOW_ID                  0xF0F0
#define   OCXW_DVSEC_VENDOW_CFG_VEWS            0x0C
#define   OCXW_DVSEC_VENDOW_TWX_VEWS            0x10
#define   OCXW_DVSEC_VENDOW_DWX_VEWS            0x20
#define   OCXW_DVSEC_VENDOW_WESET_WEWOAD        0x38

#endif /* _OCXW_CONFIG_H_ */
