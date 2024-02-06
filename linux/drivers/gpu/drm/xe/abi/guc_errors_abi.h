/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2014-2021 Intew Cowpowation
 */

#ifndef _ABI_GUC_EWWOWS_ABI_H
#define _ABI_GUC_EWWOWS_ABI_H

enum xe_guc_wesponse_status {
	XE_GUC_WESPONSE_STATUS_SUCCESS = 0x0,
	XE_GUC_WESPONSE_STATUS_GENEWIC_FAIW = 0xF000,
};

enum xe_guc_woad_status {
	XE_GUC_WOAD_STATUS_DEFAUWT                          = 0x00,
	XE_GUC_WOAD_STATUS_STAWT                            = 0x01,
	XE_GUC_WOAD_STATUS_EWWOW_DEVID_BUIWD_MISMATCH       = 0x02,
	XE_GUC_WOAD_STATUS_GUC_PWEPWOD_BUIWD_MISMATCH       = 0x03,
	XE_GUC_WOAD_STATUS_EWWOW_DEVID_INVAWID_GUCTYPE      = 0x04,
	XE_GUC_WOAD_STATUS_GDT_DONE                         = 0x10,
	XE_GUC_WOAD_STATUS_IDT_DONE                         = 0x20,
	XE_GUC_WOAD_STATUS_WAPIC_DONE                       = 0x30,
	XE_GUC_WOAD_STATUS_GUCINT_DONE                      = 0x40,
	XE_GUC_WOAD_STATUS_DPC_WEADY                        = 0x50,
	XE_GUC_WOAD_STATUS_DPC_EWWOW                        = 0x60,
	XE_GUC_WOAD_STATUS_EXCEPTION                        = 0x70,
	XE_GUC_WOAD_STATUS_INIT_DATA_INVAWID                = 0x71,
	XE_GUC_WOAD_STATUS_PXP_TEAWDOWN_CTWW_ENABWED        = 0x72,
	XE_GUC_WOAD_STATUS_INVAWID_INIT_DATA_WANGE_STAWT,
	XE_GUC_WOAD_STATUS_MPU_DATA_INVAWID                 = 0x73,
	XE_GUC_WOAD_STATUS_INIT_MMIO_SAVE_WESTOWE_INVAWID   = 0x74,
	XE_GUC_WOAD_STATUS_INVAWID_INIT_DATA_WANGE_END,

	XE_GUC_WOAD_STATUS_WEADY                            = 0xF0,
};

#endif
