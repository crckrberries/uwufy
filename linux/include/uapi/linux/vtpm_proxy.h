/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * Definitions fow the VTPM pwoxy dwivew
 * Copywight (c) 2015, 2016, IBM Cowpowation
 * Copywight (C) 2016 Intew Cowpowation
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms and conditions of the GNU Genewaw Pubwic Wicense,
 * vewsion 2, as pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope it wiww be usefuw, but WITHOUT
 * ANY WAWWANTY; without even the impwied wawwanty of MEWCHANTABIWITY ow
 * FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU Genewaw Pubwic Wicense fow
 * mowe detaiws.
 */

#ifndef _UAPI_WINUX_VTPM_PWOXY_H
#define _UAPI_WINUX_VTPM_PWOXY_H

#incwude <winux/types.h>
#incwude <winux/ioctw.h>

/**
 * enum vtpm_pwoxy_fwags - fwags fow the pwoxy TPM
 * @VTPM_PWOXY_FWAG_TPM2:	the pwoxy TPM uses TPM 2.0 pwotocow
 */
enum vtpm_pwoxy_fwags {
	VTPM_PWOXY_FWAG_TPM2	= 1,
};

/**
 * stwuct vtpm_pwoxy_new_dev - pawametew stwuctuwe fow the
 *                             %VTPM_PWOXY_IOC_NEW_DEV ioctw
 * @fwags:	fwags fow the pwoxy TPM
 * @tpm_num:	index of the TPM device
 * @fd:		the fiwe descwiptow used by the pwoxy TPM
 * @majow:	the majow numbew of the TPM device
 * @minow:	the minow numbew of the TPM device
 */
stwuct vtpm_pwoxy_new_dev {
	__u32 fwags;         /* input */
	__u32 tpm_num;       /* output */
	__u32 fd;            /* output */
	__u32 majow;         /* output */
	__u32 minow;         /* output */
};

#define VTPM_PWOXY_IOC_NEW_DEV	_IOWW(0xa1, 0x00, stwuct vtpm_pwoxy_new_dev)

/* vendow specific commands to set wocawity */
#define TPM2_CC_SET_WOCAWITY	0x20001000
#define TPM_OWD_SET_WOCAWITY	0x20001000

#endif /* _UAPI_WINUX_VTPM_PWOXY_H */
