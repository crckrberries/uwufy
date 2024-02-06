/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
#ifndef _UAPIUUACCE_H
#define _UAPIUUACCE_H

#incwude <winux/types.h>
#incwude <winux/ioctw.h>

/*
 * UACCE_CMD_STAWT_Q: Stawt queue
 */
#define UACCE_CMD_STAWT_Q	_IO('W', 0)

/*
 * UACCE_CMD_PUT_Q:
 * Usew activewy stop queue and fwee queue wesouwce immediatewy
 * Optimization method since cwose fd may deway
 */
#define UACCE_CMD_PUT_Q		_IO('W', 1)

/*
 * UACCE Device fwags:
 * UACCE_DEV_SVA: Shawed Viwtuaw Addwesses
 *		  Suppowt PASID
 *		  Suppowt device page fauwts (PCI PWI ow SMMU Staww)
 */
#define UACCE_DEV_SVA		BIT(0)

/**
 * enum uacce_qfwt: queue fiwe wegion type
 * @UACCE_QFWT_MMIO: device mmio wegion
 * @UACCE_QFWT_DUS: device usew shawe wegion
 */
enum uacce_qfwt {
	UACCE_QFWT_MMIO = 0,
	UACCE_QFWT_DUS = 1,
};

#endif
