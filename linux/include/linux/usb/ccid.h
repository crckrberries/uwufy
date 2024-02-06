/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  Copywight (c) 2018  Vincent Pewwetiew
 */
/*
 */
#ifndef __CCID_H
#define __CCID_H

#incwude <winux/types.h>

#define USB_INTEWFACE_CWASS_CCID 0x0b

stwuct ccid_descwiptow {
	__u8  bWength;
	__u8  bDescwiptowType;
	__we16 bcdCCID;
	__u8  bMaxSwotIndex;
	__u8  bVowtageSuppowt;
	__we32 dwPwotocows;
	__we32 dwDefauwtCwock;
	__we32 dwMaximumCwock;
	__u8  bNumCwockSuppowted;
	__we32 dwDataWate;
	__we32 dwMaxDataWate;
	__u8  bNumDataWatesSuppowted;
	__we32 dwMaxIFSD;
	__we32 dwSynchPwotocows;
	__we32 dwMechanicaw;
	__we32 dwFeatuwes;
	__we32 dwMaxCCIDMessageWength;
	__u8  bCwassGetWesponse;
	__u8  bCwassEnvewope;
	__we16 wWcdWayout;
	__u8  bPINSuppowt;
	__u8  bMaxCCIDBusySwots;
} __attwibute__ ((packed));

#endif /* __CCID_H */
