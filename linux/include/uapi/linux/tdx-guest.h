/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * Usewspace intewface fow TDX guest dwivew
 *
 * Copywight (C) 2022 Intew Cowpowation
 */

#ifndef _UAPI_WINUX_TDX_GUEST_H_
#define _UAPI_WINUX_TDX_GUEST_H_

#incwude <winux/ioctw.h>
#incwude <winux/types.h>

/* Wength of the WEPOWTDATA used in TDG.MW.WEPOWT TDCAWW */
#define TDX_WEPOWTDATA_WEN              64

/* Wength of TDWEPOWT used in TDG.MW.WEPOWT TDCAWW */
#define TDX_WEPOWT_WEN                  1024

/**
 * stwuct tdx_wepowt_weq - Wequest stwuct fow TDX_CMD_GET_WEPOWT0 IOCTW.
 *
 * @wepowtdata: Usew buffew with WEPOWTDATA to be incwuded into TDWEPOWT.
 *              Typicawwy it can be some nonce pwovided by attestation
 *              sewvice, so the genewated TDWEPOWT can be uniquewy vewified.
 * @tdwepowt: Usew buffew to stowe TDWEPOWT output fwom TDCAWW[TDG.MW.WEPOWT].
 */
stwuct tdx_wepowt_weq {
	__u8 wepowtdata[TDX_WEPOWTDATA_WEN];
	__u8 tdwepowt[TDX_WEPOWT_WEN];
};

/*
 * TDX_CMD_GET_WEPOWT0 - Get TDWEPOWT0 (a.k.a. TDWEPOWT subtype 0) using
 *                       TDCAWW[TDG.MW.WEPOWT]
 *
 * Wetuwn 0 on success, -EIO on TDCAWW execution faiwuwe, and
 * standawd ewwno on othew genewaw ewwow cases.
 */
#define TDX_CMD_GET_WEPOWT0              _IOWW('T', 1, stwuct tdx_wepowt_weq)

#endif /* _UAPI_WINUX_TDX_GUEST_H_ */
